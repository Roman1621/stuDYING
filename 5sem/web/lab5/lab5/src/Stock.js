import './common.css';
import './Stock.css';

import React, { useState } from 'react';
import { useSelector, useDispatch } from 'react-redux';
import { setStocks, setCurStock, enableStock, disableStock } from './store/stock-slice';
import { Line } from 'react-chartjs-2';
import Chart from 'chart.js/auto';
import axios from 'axios';

export default function Stock()
{
	let dispatch = useDispatch();
	let stocks = useSelector((state) => state.stock.stocks);
	let stocks_arr = useSelector((state) => {
		let st = state.stock.stocks;
		let ret = [];
		for(let tag in st){
			let s = st[tag];
			ret.push({tag: tag, name: s.name});
		}
		return ret;
	});

	let cur_stock_tag = useSelector((state) => state.stock.cur_stock);
	let cur_stock_name = useSelector((state) => state.stock.stocks[state.stock.cur_stock] ? state.stock.stocks[state.stock.cur_stock].name : "");
	let cur_stock_hist_arr = useSelector((state) => {
		let hist = state.stock.cur_hist;
		let ret = [];
		for(let date in hist){
			let d = hist[date];
			ret.push({date, open: d.open, high: d.high, low: d.low, close: d.close});
		}
		ret.sort((a, b) => Date.parse(b.date) - Date.parse(a.date));
		ret.splice(0, ret.length - 365*2);
		return ret;
	});
	let active_stocks = useSelector((state) => state.stock.active_stocks);

	const [hist_open, setHistOpen] = React.useState(false);
	const [hist_chart_data, setHistChartData] = React.useState({
		labels: ["тест", "ii"],
		datasets: [
			{label: "тест22",
				data: [1, 2, 3]}
		]});

	axios.get("http://localhost:4000/stocks")
		.then((res) => {
			dispatch(setStocks(res.data));
		});

	let show_stock_hist = (event) => {
		let tag = event.target.id.substr("stock_hist_".length);
		axios.get("http://localhost:4000/stocks/" + tag)
			.then((res) => {
				dispatch(setCurStock({tag: tag, hist: res.data}));
				setHistOpen(true);

				let date_labels = [];
				for(let date in res.data){
					date_labels.push(date);
				}
				date_labels.sort((a, b) => Date.parse(a) - Date.parse(b));
				date_labels.splice(0, date_labels.length - 365*2);

				let open_data = [];
				for(let i = 0; i < date_labels.length; ++i){
					open_data.push(res.data[date_labels[i]].open);
				}

				let high_data = [];
				for(let i = 0; i < date_labels.length; ++i){
					high_data.push(res.data[date_labels[i]].high);
				}

				let low_data = [];
				for(let i = 0; i < date_labels.length; ++i){
					low_data.push(res.data[date_labels[i]].low);
				}

				let close_data = [];
				for(let i = 0; i < date_labels.length; ++i){
					close_data.push(res.data[date_labels[i]].close);
				}

				setHistChartData({
					labels: date_labels,
					datasets: [
						{
							label: "Start",
							data: open_data,
							fill: false,
							backgroundColor: 'green',
							borderColor: 'green'
						},
						{
							label: "High",
							data: high_data,
							fill: false,
							backgroundColor: 'yellow',
							borderColor: 'yellow'
						},
						{
							label: "Low",
							data: low_data,
							fill: false,
							backgroundColor: 'grey',
							borderColor: 'grey'
						},
						{
							label: "Close",
							data: close_data,
							fill: false,
							backgroundColor: 'red',
							borderColor: 'red'
						}
					]
				});
		});
	}

	let close_hist = () => {
		setHistOpen(false);
	}
	let change_stock_activation = (event) => {
		let tag = event.target.id.substr("stock_".length);
		if(event.target.checked)
			dispatch(enableStock(tag));
		else
			dispatch(disableStock(tag));
	}

	return (
		<div>
			<table>
				<thead>
					<tr>
						<th className="stock_radiobox_th"></th>
						<th className="stock_radiobox_th"></th>
						<th>Company</th>
						<th>Name</th>
					</tr>
				</thead>
				<tbody>
					{stocks_arr.map((st) => (
						<tr key={st.tag}>
							<td><input type="checkbox" className="action_radio" id={"stock_" + st.tag} onChange={change_stock_activation} checked={active_stocks[st.tag] === true}/></td>
							<td><button className="stock_hist_button" id={"stock_hist_" + st.tag} onClick={show_stock_hist}>Graphic</button></td>
							<td>{st.name}</td>
							<td>{st.tag}</td>
						</tr>
						))}
				</tbody>
			</table>
			<dialog className="hist_dialog" open={hist_open}>
				[{cur_stock_tag}] {cur_stock_name}
				<button className="action_button" onClick={close_hist} style={{float: "right"}}>Close</button>
				<div className="hist_container">
					<table className="hist_table">
						<thead>
							<tr>
								<th>Date</th>
								<th>Start price</th>
								<th>Max price</th>
								<th>Min price</th>
									<th>End price</th>
								</tr>
							</thead>
							<tbody>
								{cur_stock_hist_arr.map((day) => (
									<tr key={day.date}>
										<td>{day.date}</td>
										<td>{day.open}</td>
										<td>{day.high}</td>
										<td>{day.low}</td>
										<td>{day.close}</td>
									</tr>
								))}
							</tbody>
						</table>
					<div> 
						<Line data={hist_chart_data} options={{animation: {duration: 0}, pointRadius: 0, events: []}}/> 
					</div>
				</div>
			</dialog>
		</div>
	);
}
