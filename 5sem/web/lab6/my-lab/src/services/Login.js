class LoginService
{
	login(axios, store, on_login, on_error)
	{
		axios.post('http://localhost:3100/login', {token: sessionStorage['token']})
			.then((res) => {
				if(!res.data.error){
					store.commit('set_name', res.data.name);
					store.commit('set_money', res.data.money);
					store.commit('set_current_date', res.data.date);

					let prices = [];
					for(let tag in res.data.cur_prices)
						prices.push({tag, price: res.data.cur_prices[tag]});
					prices.sort((a, b) => {
						if(a.tag < b.tag) return -1;
						else if(a.tag > b.tag) return 1;
						return 0;
					});

					store.commit('set_stock_prices', prices);
					store.commit('set_bought_stocks', res.data.bought_stocks);
					store.commit('set_income', res.data.income);
					on_login();
				}
				else
					on_error(res.data.error);
			});
	}
}

export default new LoginService();
