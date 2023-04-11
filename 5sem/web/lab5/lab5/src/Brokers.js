import './Brokers.css';
import './common.css';

import React, { Component, useState } from 'react';
import { useSelector, useDispatch } from 'react-redux';
import { setBrokers } from './store/broker-slice';
import axios from 'axios';

export default function Brokers()
{
	let dispatch = useDispatch();
	let brokers = useSelector((state) => state.broker.brokers);
	let brokers_arr = useSelector((state) => {
		let br = state.broker.brokers;
		let ret = [];
		for(let id in br){
			let b = br[id];
			ret.push({name: b.name, money: b.money, id: "broker_" + id});
		}
		return ret;
	});
	let selected_broker_id = useSelector((state) => state.broker.selected);

	const [broker_name, setBrokerName] = useState('');
	const [broker_money, setBrokerMoney] = useState(0);
	const [selected_broker, selectBroker] = useState('');

	axios.get("http://localhost:4000/brokers")
		.then((res) => {
			dispatch(setBrokers(res.data));
		});


	let select_broker = (event) => {
		let sel = event.target.id.substr("broker_".length);
		selectBroker(sel);
		setBrokerName(brokers[sel].name);
		setBrokerMoney(brokers[sel].money);
	};

	let add_broker = () => {
		axios.post("http://localhost:4000/brokers",
					{name: broker_name, money: Number(broker_money)})
		.then((res) => {
			dispatch(setBrokers(res.data));
		});
	}
	let change_broker = () => {
		if(!selected_broker)
			return;
		axios.put("http://localhost:4000/brokers/" + selected_broker,
					{name: broker_name, money: Number(broker_money)})
		.then((res) => {
			dispatch(setBrokers(res.data));
		});
	}
	let delete_broker = () => {
		if(!selected_broker)
			return;
		axios.delete("http://localhost:4000/brokers/" + selected_broker)
		.then((res) => {
			dispatch(setBrokers(res.data));
		});
	}

	return (
		<div>
			<div className="action_pane">
				Broker Name:
				<input type="text" className="action_input" value={broker_name} onChange={e => setBrokerName(e.target.value)}></input>
				Amount of funds:
				<input type="number" className="action_input" value={broker_money} onChange={e => setBrokerMoney(e.target.value)}></input>
				<button className="action_button" onClick={add_broker}>Add</button>
				<button className="action_button" onClick={change_broker}>Edit</button>
				<button className="action_button" onClick={delete_broker}>Remove</button>
			</div>
			<table>
				<thead>
					<tr>
					<th className="broker_radiobox_th"></th>
						<th>Broker nаme</th>
						<th>Amount of funds</th>
					</tr>
				</thead>
				<tbody>
					{brokers_arr.map((br) => (
						<tr key={br.id}>
							<td><input type="radio" name="broker_id_radio" className="action_radio" id={br.id} onChange={select_broker}/></td>
							<td>{br.name}</td>
							<td>{br.money}</td>
						</tr>
					))}
				</tbody>
			</table>
		</div>
	);
}
