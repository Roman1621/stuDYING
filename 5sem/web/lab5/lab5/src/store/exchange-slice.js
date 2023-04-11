import { createSlice } from '@reduxjs/toolkit';

export const exchangeSlice = createSlice({
	name: 'exchange',
	initialState: {
		begin_date: "",
		date_delay: 1
	},
	reducers: {
		setBeginDate: (state, action) => {
			state.begin_date = action.payload;
		},
		setDateDelay: (state, action) => {
			state.date_delay = action.payload;
		}
	}
});

export const { setBeginDate, setDateDelay } = exchangeSlice.actions;
export default exchangeSlice.reducer;
