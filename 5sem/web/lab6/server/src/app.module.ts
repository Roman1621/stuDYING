import { Module } from '@nestjs/common';
import { HttpModule } from '@nestjs/axios';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { LoginService } from './login/login.service';
import { LoginController } from './login/login.controller';
import { ExchangeService } from './exchange/exchange.service';
import { ExchangeController } from './exchange/exchange.controller';
import { AdminController } from './admin/admin.controller';
import { AdminService } from './admin/admin.service';

@Module({
	imports: [HttpModule],
	controllers: [AppController, LoginController, ExchangeController, AdminController],
	providers: [AppService, LoginService, ExchangeService, AdminService],
})
export class AppModule {}
