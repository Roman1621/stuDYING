<template>
	<table>
		<tr>
			<th>Username</th>
			<th>Balance</th>
			<th>Number of actions</th>
			<th>Profit</th>
		</tr>
		<tr v-for="broker in broker_data" :key="broker.name">
			<td>{{broker.name}}</td>
			<td>{{broker.money}}</td>
			<td>{{broker.stocks}}</td>
			<td>{{broker.income}}</td>
		</tr>
	</table>
</template>

<script>
import ExchangeService from '../services/Exchange';

export default
{
	name: 'AdminComponent',
	components: {},

	data() { return {
					broker_data: []
				}},

	created() {
		this.update_info();
		ExchangeService.set_stock_price_ref(this.$store, () => this.update_info());
	},
	methods: {
		update_info()
		{
			this.axios.get("http://localhost:3100/admin/info")
				.then((res) => {
					let broker_data = [];
					for(let token in res.data.brokers_data){
						let broker = {};
						broker.name = res.data.brokers_data[token].name;
						broker.money = res.data.brokers_money[token] ? res.data.brokers_money[token].toFixed(3) : res.data.brokers_data[token].money.toFixed(3);
						if(res.data.brokers_income[token]){
							broker.income = "";
							for(let tag in res.data.brokers_income[token])
								broker.income += tag + ": " + (res.data.brokers_income[token][tag] + (this.$store.state.stock_prices_raw[tag] ? this.$store.state.stock_prices_raw[tag] * res.data.brokers_stocks[token][tag] : 0)).toFixed(3) + ", ";
							broker.income = broker.income.substr(0, broker.income.length - 2);
						}
						if(res.data.brokers_stocks[token]){
							broker.stocks = "";
							for(let tag in res.data.brokers_stocks[token])
								broker.stocks += tag + ": " + res.data.brokers_stocks[token][tag].toFixed(3) + ", ";
							broker.stocks = broker.stocks.substr(0, broker.stocks.length - 2);
						}
						broker_data.push(broker);
					}
					this.broker_data = broker_data;
				});
		}
	}
}
</script>

<style scoped>
table {
	margin-top: 2vh;
	width: 100%;

	font-size: 2.5vh;

	border-collapse: collapse;
	border: 2px solid black;
}
td {
	border: 2px solid black;
}
th {
	border: 2px solid black;
}
</style>
