import { WebSocketGateway, WebSocketServer, SubscribeMessage} from '@nestjs/websockets';
import { Socket, Server } from 'socket.io';

@WebSocketGateway()
export class ExchangeGateway
{
	@WebSocketServer() server;

	broadcast(event: string, message: any)
	{
		const msg = JSON.stringify(message);
		this.server.emit(event, msg);
	}
}

