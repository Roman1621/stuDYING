import { Test, TestingModule } from '@nestjs/testing';
import { ExchangeGateway } from './exchange.gateway';

describe('ExchangeGateway', () => {
  let gateway: ExchangeGateway;

  beforeEach(async () => {
    const module: TestingModule = await Test.createTestingModule({
      providers: [ExchangeGateway],
    }).compile();

    gateway = module.get<ExchangeGateway>(ExchangeGateway);
  });

  it('should be defined', () => {
    expect(gateway).toBeDefined();
  });
});
