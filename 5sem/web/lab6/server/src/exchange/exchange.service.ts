import { Injectable } from '@nestjs/common';
import { HttpService } from '@nestjs/axios';
import { map } from 'rxjs/operators';
import { lastValueFrom } from 'rxjs';
import { readFileSync } from 'fs';

@Injectable()
export class ExchangeService 
{
	stocks_data = {};

	brokers_money = {};
	brokers_stocks = {};
	brokers_income = {};

	cur_date = "";
	cur_prices = {};

	constructor(private readonly httpService: HttpService)
	{
		let fd = readFileSync('../../lab5/stocks.json');
		this.stocks_data = JSON.parse(fd.toString());
		this.getCurrentPrices();
	}

	setBrokerMoney(token: string, money: number): number
	{
		if(!this.brokers_money[token])
			this.brokers_money[token] = money;
		return this.brokers_money[token];
	}
	changeBrokerStocks(token: string, tag: string, amt: number)
	{
		if(!this.brokers_stocks[token])
			this.brokers_stocks[token] = {};
		if(!this.brokers_stocks[token][tag] && amt > 0)
			this.brokers_stocks[token][tag] = amt;
		else if(this.brokers_stocks[token][tag])
			this.brokers_stocks[token][tag] = Math.max(this.brokers_stocks[token][tag] + amt, 0);
	}
	changeBrokerIncome(token: string, tag: string, mon: number)
	{
		if(!this.brokers_income[token])
			this.brokers_income[token] = {};
		if(!this.brokers_income[token][tag])
			this.brokers_income[token][tag] = mon;
		else
			this.brokers_income[token][tag] += mon;
	}

	async getCurrentPrices()
	{
		let res = await lastValueFrom(this.httpService.get('http://localhost:4000/exchange/date').pipe(
			map(resp => resp.data)
		));
		if(this.cur_date != res){
			this.cur_date = res;
			if(this.cur_date !== "undefined")
				this.getCurrentPricesSync();
			
		}
	}

	getCurrentPricesSync()
	{
		for(let tag in this.stocks_data){
			let day_hist = this.stocks_data[tag].hist[this.cur_date];
			if(day_hist)
				this.cur_prices[tag] = day_hist.open;
			else{
				let date = new Date(this.cur_date);
				for(let i = 0; i < 4; ++i){
					date.setDate(date.getDate() - 1);
					let iso_date = "";
					try {
						iso_date = date.toISOString();
						iso_date = iso_date.substr(0, iso_date.indexOf('T'));
					}
					catch {}
					if(iso_date != ""){
						day_hist = this.stocks_data[tag].hist[iso_date];
						if(day_hist){
							this.cur_prices[tag] = day_hist.open;
							break;
						}
					}
				}
			}
		}
	}


	async tryBuyStock(token: string, tag: string, amt: number)
	{
		if(!this.brokers_money[token]) return {error: "Unknown user"};
		await this.getCurrentPrices();
		let topay = amt * this.cur_prices[tag];
		if(topay === null) return {error: "No such action"};
		if(amt === undefined || amt === null) return {error: "Wrong action count"};
		if(this.brokers_money[token] < topay) return {error: "No money"};

		this.changeBrokerStocks(token, tag, amt);
		this.changeBrokerIncome(token, tag, -topay);
		this.brokers_money[token] -= topay;
		return {money: this.brokers_money[token], stocks: this.brokers_stocks[token], income: this.brokers_income[token]};
	}

	async trySellStock(token: string, tag: string, amt: number)
	{
		if(!this.brokers_money[token]) return {error: "Unknown user"};

		await this.getCurrentPrices();
		if(!this.brokers_stocks[token]) amt = 0;
		else if(!this.brokers_stocks[token][tag]) amt = 0;
		else amt = Math.min(this.brokers_stocks[token][tag], amt);
		let togain = amt * this.cur_prices[tag];

		this.changeBrokerStocks(token, tag, -amt);
		this.changeBrokerIncome(token, tag, togain);
		this.brokers_money[token] += togain;
		return {money: this.brokers_money[token], stocks: this.brokers_stocks[token], income: this.brokers_income[token]};
	}
}
