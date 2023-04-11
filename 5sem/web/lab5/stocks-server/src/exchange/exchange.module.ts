import { Module } from '@nestjs/common';
import { ExchangeGateway } from '../exchange.gateway';
import { ExchangeController } from './exchange.controller';
import { ExchangeService } from './exchange.service';

@Module({
	controllers: [ExchangeController],
	providers: [ExchangeService, ExchangeGateway]
})
export class ExchangeModule {}
