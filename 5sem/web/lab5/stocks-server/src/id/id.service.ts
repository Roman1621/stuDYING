import { Injectable } from '@nestjs/common';

@Injectable()
export class IdService
{
	generateId(len = 8)
	{
		let id = "";
		let chars = "1234567890";
		for(let i = 0; i < len; ++i)
			id += chars[Math.floor(Math.random() * chars.length)];
		return id;
	}
}
