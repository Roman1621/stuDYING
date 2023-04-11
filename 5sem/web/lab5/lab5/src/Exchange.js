import './common.css';
import './Exchange.css';

import React, { useState } from 'react';
import { useSelector, useDispatch } from 'react-redux';
import { setBeginDate, setDateDelay } from './store/exchange-slice';
import axios from 'axios';
import socketio from 'socket.io-client';

export default function Exchange()
{
	let dispatch = useDispatch();
	let begin_date = useSelector((state) => state.exchange.begin_date);
	let date_delay = useSelector((state) => state.exchange.date_delay);
	let active_stocks = useSelector((state) => state.stock.active_stocks);

	let change_begin_date = (event) => {
		dispatch(setBeginDate(event.target.value));
	}
	let change_date_delay = (event) => {
		dispatch(setDateDelay(Number(event.target.value)));
	}

	let begin_exchange = () => {

		if(begin_date == "" || active_stocks.length == 0)
			return;
		let _stocks = [];
		for(let tag in active_stocks)
			_stocks.push(tag);
		axios.post("http://localhost:4000/exchange",
					{begin_date, date_delay, active_stocks: _stocks});
	}

	const [stocks_price, setStocksPrice] = React.useState([]);
	const [exchange_date, setExchangeDate] = React.useState("");
	let socket = socketio.connect("http://localhost:4000");
	socket.on('stock-price-change', (data) =>{
		data = JSON.parse(data);
		let res = [];
		for(let tag in data.prices){
			res.push({tag, price: data.prices[tag]});
		}
		setStocksPrice(res);
		setExchangeDate(data.date);
	});

	return (
		<div>
			<div className="action_pane">
			Start date:
			<input type="date" className="action_input" value={begin_date} onChange={change_begin_date}/>
			Time interval:
			<input type="number" className="action_input" value={date_delay} onChange={change_date_delay} min="1" max="60"/>
			<button className="action_button" onClick={begin_exchange}>Start</button>
			</div>

			<div className="exchange_info_pane">
				Current date: <b>{exchange_date}</b><br/>
			</div>

			<table>
				<thead>
					<tr>
						<th>Name</th>
						<th>Cost</th>
					</tr>
				</thead>
				<tbody>
					{stocks_price.map((stock) => (
						<tr key={stock.tag}>
							<td>{stock.tag}</td>
							<td>{stock.price}</td>
						</tr>
					))}
				</tbody>
			</table>
		</div>
	);
}
