import { Controller, Get, Post, Put, Delete, Body, Param } from '@nestjs/common';
import { BrokersService, Broker } from './brokers.service';

export class BrokerBody
{
	name: string;
	money: number;
}

@Controller('brokers')
export class BrokersController {
	constructor(private readonly brokersService: BrokersService) {}

	@Get()
	getBrokers(): string {
		return this.brokersService.getAllBrokers();
	}
	@Post()
	addBroker(@Body() body: BrokerBody): string {
		this.brokersService.addBroker(new Broker(body.name, body.money));
		return this.brokersService.getAllBrokers();
	}
	@Put(":id")
	changeBroker(@Body() body: BrokerBody, @Param("id") id): string {
		this.brokersService.changeBroker(id, new Broker(body.name, body.money));
		return this.brokersService.getAllBrokers();
	}
	@Delete(":id")
	deleteBroker(@Param("id") id): string {
		this.brokersService.deleteBroker(id);
		return this.brokersService.getAllBrokers();
	}
}
