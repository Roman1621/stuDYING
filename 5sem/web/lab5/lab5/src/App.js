import './App.css';

import Brokers from './Brokers';
import Exchange from './Exchange';
import Stock from './Stock';

import React from 'react';
import ReactDOM from 'react-dom/client';
import {Routes, Route, BrowserRouter} from 'react-router-dom';
import {useNavigate} from 'react-router-dom';

export default function App()
{
	const navigate = useNavigate();
	const navBrokers = () => { navigate("/brokers"); };
	const navStock = () => { navigate("/stock"); };
	const navExchange = () => { navigate("/exchange"); };
	
	return (
		<div>
			<div className="menu_pane">
				<button className="menu_button" onClick={navBrokers}>Brokers</button>
				<button className="menu_button" onClick={navStock}>Actions</button>
				<button className="menu_button" onClick={navExchange}>Settings</button>
			</div>
			<Routes>
				<Route path="/brokers" element={<Brokers/>}/>
				<Route path="/exchange" element={<Exchange/>}/>
				<Route path="/stock" element={<Stock/>}/>
			</Routes>
		</div>
	);
}
