import { Injectable } from '@nestjs/common';
import { readFileSync } from 'fs';

@Injectable()
export class StocksService
{
	stocks_data;

	constructor()
	{
		let fd = readFileSync('../stocks.json');
		this.stocks_data = JSON.parse(fd.toString());
	}

	getAllStocks(): string
	{
		let ret = {};
		for(let tag in this.stocks_data)
			ret[tag] = {name: this.stocks_data[tag].name};
		return JSON.stringify(ret);
	}
	getStockHist(tag: string): string
	{
		return JSON.stringify(this.stocks_data[tag].hist);
	}
}
