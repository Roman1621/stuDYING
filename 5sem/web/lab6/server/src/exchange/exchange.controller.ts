import { Controller, Body, Post } from '@nestjs/common';
import { ExchangeService } from './exchange.service';

export class StockOpBody
{
	user_token: string;
	tag: string;
	amt: number;
}

@Controller('exchange')
export class ExchangeController
{
	constructor(private readonly exchangeService: ExchangeService) {}

	@Post('buy')
	async buyStocks(@Body() body: StockOpBody)
	{
		return await this.exchangeService.tryBuyStock(body.user_token, body.tag, body.amt);
	}
	@Post('sell')
	async sellStocks(@Body() body: StockOpBody)
	{
		return await this.exchangeService.trySellStock(body.user_token, body.tag, body.amt);
	}
}
