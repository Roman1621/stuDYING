import { createSlice } from '@reduxjs/toolkit';

export const stockSlice = createSlice({
	name: 'stock',
	initialState: {
		stocks: {},
		cur_stock: "",
		cur_hist: {},

		active_stocks: {}
	},
	reducers: {
		setStocks: (state, action) => {
			state.stocks = action.payload;
		},
		setCurStock: (state, action) => {
			state.cur_stock = action.payload.tag;
			state.cur_hist = action.payload.hist;
		},

		enableStock: (state, action) => {
			state.active_stocks[action.payload] = true;
		},
		disableStock: (state, action) => {
			state.active_stocks[action.payload] = false;
		}
	}
});

export const { setStocks, setCurStock, enableStock, disableStock } = stockSlice.actions;
export default stockSlice.reducer;
