import { Injectable } from '@nestjs/common';
import { readFileSync } from 'fs';
import { ExchangeService } from '../exchange/exchange.service';

@Injectable()
export class LoginService
{
	brokers_data;

	constructor(private readonly exchangeService: ExchangeService) {
		let fd = readFileSync('../../lab5/brokers.json');
		this.brokers_data = JSON.parse(fd.toString());
	}

	loginUser(token: string) {
		let broker = this.brokers_data[token];
		if(broker){
			this.exchangeService.getCurrentPricesSync();
			let cur_prices = {};
			let bought_stocks = this.exchangeService.brokers_stocks[token] ? this.exchangeService.brokers_stocks[token] : {};
			for(let tag in bought_stocks)
				cur_prices[tag] = this.exchangeService.cur_prices[tag];
			let income = this.exchangeService.brokers_income[token] ? this.exchangeService.brokers_income[token] : {};

		return {name: broker.name, money: this.exchangeService.setBrokerMoney(token, this.brokers_data[token].money), date: this.exchangeService.cur_date, bought_stocks, cur_prices, income};
		}
		else
			return {error: "No such broker \"" + token + '"'};
	}
}
