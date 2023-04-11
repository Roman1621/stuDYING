import { Controller, Get, Post, Body } from '@nestjs/common';
import { ExchangeService } from './exchange.service';

export class ExchangeBody {
	begin_date: string;
	date_delay: number;
	active_stocks: string[];
}

@Controller('exchange')
export class ExchangeController {
	constructor(private readonly exchangeService: ExchangeService) {}

	@Post()
	beginExchange(@Body() body: ExchangeBody): void
	{
		this.exchangeService.beginExchange(body.begin_date, body.date_delay, body.active_stocks);
	}
	@Get('date')
	getDate(): string
	{
		if(this.exchangeService.current_date){
			let iso_date = this.exchangeService.current_date.toISOString();
			iso_date = iso_date.substr(0, iso_date.indexOf('T'));
			return iso_date;
		}
		else return "undefined";
	}
}
