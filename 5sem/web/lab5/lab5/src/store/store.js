import { configureStore } from '@reduxjs/toolkit';
import brokerReducer from './broker-slice';
import stockReducer from './stock-slice';
import exchangeReducer from './exchange-slice';

export const store = configureStore({
	reducer: {
		broker: brokerReducer,
		stock: stockReducer,
		exchange: exchangeReducer
	},
});

