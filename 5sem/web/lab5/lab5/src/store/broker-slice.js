import { createSlice } from '@reduxjs/toolkit';

export const brokerSlice = createSlice({
	name: 'broker',
	initialState: {
		brokers: {}
	},
	reducers: {
		setBrokers: (state, action) => {
			state.brokers = action.payload;
		}
	}
});

export const { setBrokers } = brokerSlice.actions;
export default brokerSlice.reducer;
