import { Controller, Post, Body } from '@nestjs/common';
import { LoginService } from './login.service';

export class LoginBody
{
	token: string;
}

@Controller('login')
export class LoginController
{
	constructor(private readonly loginService: LoginService) {}

	@Post()
	loginUser(@Body() body: LoginBody): string
	{
		return JSON.stringify(this.loginService.loginUser(body.token));
	}
}
