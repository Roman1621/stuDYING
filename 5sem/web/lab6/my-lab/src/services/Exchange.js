import io from 'socket.io-client';

class ExchangeService {
	constructor()
	{
		this.socket = io("localhost:4000");
	}

	set_stock_price_ref(ref, on_change)
	{
		this.socket.on('stock-price-change', (data) => {
			data = JSON.parse(data);
			let prices = [];
			for(let tag in data.prices)
				prices.push({tag, price: data.prices[tag]});
			prices.sort((a, b) => {
				if(a.tag < b.tag) return -1;
				else if(a.tag > b.tag) return 1;
				return 0;
			});

			ref.commit('set_stock_prices', prices);
			ref.commit('set_stock_prices_raw', data.prices);
			ref.commit('set_current_date', data.date);
			ref.commit('append_stock_hist', {date: data.date, day: data.prices});
			if(on_change)
				on_change();
		});
	}
}

export default new ExchangeService();
