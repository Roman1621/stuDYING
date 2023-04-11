import { Injectable } from '@nestjs/common';
import { ExchangeService } from '../exchange/exchange.service';
import { LoginService } from '../login/login.service';

@Injectable()
export class AdminService
{
	constructor(private readonly exchangeService : ExchangeService, private readonly loginService: LoginService) {}

	getAllInfo()
	{
		return {
			brokers_money: this.exchangeService.brokers_money,
			brokers_stocks: this.exchangeService.brokers_stocks,
			brokers_income: this.exchangeService.brokers_income,
			brokers_data: this.loginService.brokers_data
		};
	}
}
