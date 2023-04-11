<template>
	<div style="font-size: 3vh">
		Current date: <b>{{$store.state.current_date == "undefined" ? "" : $store.state.current_date}}</b><br>
		Money: <b>{{$store.state.money.toFixed(3)}}</b>
		<div class="trade_error">{{msg_error}}</div><br>
		<button class="hist_button" v-on:click="open_hist">Trade story</button>
	</div>
	<table>
		<tr>
			<th>Index</th>
			<th>Cost</th>
			<th>Purchased</th>
			<th>Profit</th>
			<th style="width: 12vw;">Actions</th>
		</tr>
		<tr v-for="stock in $store.state.stock_prices" :key="stock.tag">
			<td>{{stock.tag}}</td>
			<td>{{stock.price.toFixed(3)}}</td>
			<td>{{$store.state.bought_stocks[stock.tag] ? $store.state.bought_stocks[stock.tag] : 0}}</td>
			<td>{{$store.state.income[stock.tag] ? ($store.state.income[stock.tag] + stock.price * ($store.state.bought_stocks[stock.tag] ? $store.state.bought_stocks[stock.tag] : 0)).toFixed(3) : 0}}</td>
			<td>
				<input class="action_input" type="number" min="1" v-model="count[stock.tag]"/>
				<button class="action_button" :id=stock.tag v-on:click="buy">+</button>
				<button class="action_button" :id=stock.tag v-on:click="sell">–</button>
			</td>
		</tr>
	</table>

	<dialog class="hist_dialog" v-if="hist_open" open>
		<button class="hist_button" style="float:right" v-on:click="close_hist">X</button>
		<div style="height:100%">
		<Line
				:chart-options="histChartOptions"
				:chart-data="histChartData"
				:styles="{height:'95%'}"
			/>
		</div>
	</dialog>
</template>

<script>
import ExchangeService from '../services/Exchange';
import { Line } from 'vue-chartjs';
import { Chart as ChartJS, Title, Tooltip, Legend, LineElement, CategoryScale, LinearScale, PointElement } from 'chart.js';

ChartJS.register(Title, Tooltip, Legend, LineElement, CategoryScale, LinearScale, PointElement);

export default
{
	name: 'TradeComponent',
	components: {Line},

	data() { return {
						count: {},
						msg_error: "",

						histChartOptions: {responsive: true, maintainAspectRatio:false},
						histChartData: {
							labels: [],	
							datasets: []
						},

						hist_open: false
					}},
	created() {
		ExchangeService.set_stock_price_ref(this.$store, () => {
			let labels = [];
			let sets = [];
			let colors = ['green', 'blue', 'red', 'orange', 'black'];
			for(let date in this.$store.state.stock_hist){
				if(new Date(date) > new Date(this.$store.state.current_date))
					continue;

				labels.push(date);
				let day = this.$store.state.stock_hist[date];
				for(let tag in day){
					let found_tag = false;
					for(let i = 0; i < sets.length; ++i)
						if(sets[i].label == tag){
							sets[i].data.push(day[tag]);
							found_tag = true;
						}
					if(!found_tag)
						sets.push({label: tag, data: [day[tag]], borderColor: colors[sets.length % colors.length]});
				}
			}
			this.histChartData.labels = labels;
			this.histChartData.datasets = sets;
		});
	},
	methods: {
		buy(event)
		{
			let tag = event.target.id;
			let amt = this.count[tag];

			this.msg_error = "";
			this.axios.post("http://localhost:3100/exchange/buy", {user_token: sessionStorage['token'], tag, amt})
				.then((res) => {
					if(!res.data.error){
						this.$store.commit('set_money', res.data.money);
						this.$store.commit('set_bought_stocks', res.data.stocks);
						this.$store.commit('set_income', res.data.income);
					}
					else
						this.msg_error = res.data.error;
				});
		},
		sell(event)
		{
			let tag = event.target.id;
			let amt = this.count[tag];


			this.msg_error = "";
			this.axios.post("http://localhost:3100/exchange/sell", {user_token: sessionStorage['token'], tag, amt})
				.then((res) => {
					if(!res.data.error){
						this.$store.commit('set_money', res.data.money);
						this.$store.commit('set_bought_stocks', res.data.stocks);
						this.$store.commit('set_income', res.data.income);
					}
					else
						this.msg_error = res.data.error;
				});
		},

		open_hist() { this.hist_open = true; },
		close_hist() { this.hist_open = false; }
	}
}
</script>

<style scoped>
table {
  margin-top: 1vh;
  width: 97vw;
  font-size: 3vh;
}

.action_button {
  background-color: transparent;
  margin: 1px;
  height: auto;
  width: 33%;
  font-size: 2.5vh;
  color: white;
  border-radius: 5px;
}
.action_input {
	font-size: 2.5vh;
	font-weight: bold;
	width: 8vw;
}

.trade_error {
	background-color: transparent;
	font-size: 3vh;
	width: fit-content;
	float: right;
}

.hist_dialog {
	top: 15vh;
	width: 70vw;
	height: 70vh;	
}
.hist_button {
	margin-top: 0.5vh;
	font-size: 2.5vh;
	font-weight: bold;
	color: white;
	background-color: black;
}
</style>
