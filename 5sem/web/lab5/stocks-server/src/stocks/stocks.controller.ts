import { Controller, Get, Param } from '@nestjs/common';
import { StocksService } from './stocks.service';

@Controller('stocks')
export class StocksController
{
	constructor(private readonly stocksService: StocksService) {}

	@Get()
	getStocks(): string
	{
		return this.stocksService.getAllStocks();
	}
	@Get(":tag")
	getStockHist(@Param("tag") tag): string
	{
		return this.stocksService.getStockHist(tag);
	}
}
