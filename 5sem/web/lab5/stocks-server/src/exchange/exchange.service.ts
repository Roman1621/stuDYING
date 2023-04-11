import { Inject, Injectable } from '@nestjs/common';
import { ExchangeGateway } from '../exchange.gateway';
import { readFileSync } from 'fs';

@Injectable()
export class ExchangeService
{
	exchange_interval: any = null;
	stocks_data;

	current_date: Date;
	current_stocks: string[];
	prev_prices: any = {};
	price_didnt_change: 0;

	constructor(private readonly exchangeGateway: ExchangeGateway)
	{
		let fd = readFileSync('../stocks.json');
		this.stocks_data = JSON.parse(fd.toString());
	}

	beginExchange(begin_date: string, date_delay: number, active_stocks: string[]): void {
		date_delay = date_delay < 1 ? 1 : date_delay;
		date_delay = date_delay > 60 ? 60 : date_delay;
		if(this.exchange_interval)
			clearInterval(this.exchange_interval);

		this.current_date = new Date(begin_date);
		this.current_stocks = active_stocks;
		this.price_didnt_change = 0;

		this.exchange_interval = setInterval(() => {
			let cur_prices = {};
			let price_changed = false;
			let iso_date = this.current_date.toISOString();
			iso_date = iso_date.substr(0, iso_date.indexOf('T'));
			for(let i = 0; i < this.current_stocks.length; ++i){
				let tag = this.current_stocks[i];
				let st = this.stocks_data[tag];
				if(!st) { cur_prices[tag] = this.prev_prices[tag]; continue; }
				let day_info = st.hist[iso_date];
				if(!day_info) { cur_prices[tag] = this.prev_prices[tag]; continue; }
				cur_prices[tag] = day_info.open;
				price_changed = true;
			}
			if(!price_changed)
				++this.price_didnt_change;
			else
				this.price_didnt_change = 0;
			if(this.price_didnt_change >= 4){
				clearInterval(this.exchange_interval);
				this.exchange_interval = null;
			}
			
			this.exchangeGateway.broadcast('stock-price-change', {prices: cur_prices, date: iso_date});

			this.prev_prices = cur_prices;
			this.current_date.setDate(this.current_date.getDate() + 1);

		}, date_delay * 1000);
	}
}
