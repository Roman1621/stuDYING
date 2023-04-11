import { Injectable } from '@nestjs/common';
import { readFileSync, writeFileSync } from 'fs';
import { IdService } from '../id/id.service';

export class Broker {
	name; money;
	constructor(name: string, money: number)
	{ this.name = name; this.money = money; }
}

@Injectable()
export class BrokersService {
	brokers_data;

	constructor(private readonly idService: IdService) {
		let fd = readFileSync('../brokers.json');
		this.brokers_data = JSON.parse(fd.toString());
	}

	writeBrokersData(): void {
		writeFileSync('../brokers.json', JSON.stringify(this.brokers_data));
	}

	getAllBrokers(): string {
		return JSON.stringify(this.brokers_data);
	}
	addBroker(br: Broker): void {
		this.brokers_data[this.idService.generateId()] = {name: br.name, money: br.money};
		this.writeBrokersData();
	}
	changeBroker(id: string, br: Broker) : void {
		if(this.brokers_data[id])
			this.brokers_data[id] = {name: br.name, money: br.money};
		this.writeBrokersData();
	}
	deleteBroker(id: string) : void {
		if(this.brokers_data[id])
			delete this.brokers_data[id];
		this.writeBrokersData();
	}
}
