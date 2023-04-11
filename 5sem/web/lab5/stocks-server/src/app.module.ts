import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { BrokersController } from './brokers/brokers.controller';
import { BrokersService } from './brokers/brokers.service';
import { IdService } from './id/id.service';
import { StocksController } from './stocks/stocks.controller';
import { StocksService } from './stocks/stocks.service';
import { ExchangeModule } from './exchange/exchange.module';

@Module({
	imports: [ExchangeModule],
	controllers: [AppController, BrokersController, StocksController],
	providers: [AppService, BrokersService, IdService, StocksService]
})
export class AppModule {}
