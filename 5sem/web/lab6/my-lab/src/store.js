import { createStore } from 'vuex';
export default createStore({
	state() { return {
						stock_prices: {},
						stock_prices_raw: {},
						stock_hist: {},

						current_date: "",
						money: 0,
						name: "",

						bought_stocks: {},
						income: {}
					}},
	mutations: {
		set_stock_prices(state, prices) { state.stock_prices = prices; },
		set_stock_prices_raw(state, prices) { state.stock_prices_raw = prices; },
		append_stock_hist(state, payload) { state.stock_hist[payload.date] = payload.day; },

		set_current_date(state, date) { state.current_date = date; },
		set_money(state, money) { state.money = money; },
		set_name(state, name) { state.name = name; },

		set_bought_stocks(state, stocks) { state.bought_stocks = stocks; },
		set_income(state, income) { state.income = income; }
	}
});
