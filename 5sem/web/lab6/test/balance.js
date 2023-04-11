const ppt = require("puppeteer");

let params = {
	login_token: "1",
	stock: {
		amount: 3,
		delta: 0.25
	},
	state: {}
};

function delay(ms) { return new Promise(resolve => setTimeout(resolve, ms)); }

let expects = {
	total: 0,
	passed: 0
};
function expectToEqual(name, val, eq) {
	++expects.total;
	if(val != eq)
		console.log("\x1b[31m" + "Didn't pass expect \"" + name + "\": \"" + val + "\" is NOT equal to \"" + eq + '"' + "\x1b[0m");
	else{
		console.log("\x1b[32m" + "Passed expect \"" + name + "\": \"" + val + "\" is equal to \"" + eq + '"' + "\x1b[0m");
		++expects.passed;
	}
}
function expectToLE(name, val, eq) {
	++expects.total;
	if(val > eq)
		console.log("\x1b[31m" + "Didn't pass expect \"" + name + "\": \"" + val + "\" is NOT less or equal to \"" + eq + '"' + "\x1b[0m");
	else{
		console.log("\x1b[32m" + "Passed expect \"" + name + "\": \"" + val + "\" is less or equal to \"" + eq + '"' + "\x1b[0m");
		++expects.passed;
	}
}
function expectsEnd()
{
	console.log("Expects:");
	console.log("\tTotal:", expects.total);
	console.log("\tPassed:", expects.passed);
}

async function login(page)
{
	await page.goto('http://localhost:8080/#/login');
	await page.waitForSelector('.login_textbox');
	await page.focus('.login_textbox');
	await page.keyboard.type(params.login_token);
	await page.click('.login_button');
}
async function open_stocks(page)
{
	await page.goto('http://localhost:8080/#/trade');
	await page.waitForSelector('.hist_button');
}
async function buy_stock(page)
{
	await page.waitForSelector('b:nth-of-type(2)');
	let prev_balance = Number(await page.$eval('b:nth-of-type(2)', e => e.innerHTML));
	await page.waitForSelector('td:nth-of-type(3)');
	let prev_amt = Number(await page.$eval('td:nth-of-type(3)', e => e.innerHTML));
	await page.waitForSelector('td:nth-of-type(2)');
	let stock_price = Number(await page.$eval('td:nth-of-type(2)', e => e.innerHTML));
	await page.waitForSelector('.action_input');
	await page.focus('.action_input');
	await page.keyboard.type(params.stock.amount.toString());
	await page.click('.action_button:nth-of-type(1)');

	await delay(1000);

	await page.waitForSelector('b:nth-of-type(2)');
	let cur_balance = Number(await page.$eval('b:nth-of-type(2)', e => e.innerHTML));
	expectToLE("balance change when buying stocks", Math.abs(cur_balance.toFixed(2) - (prev_balance - stock_price * params.stock.amount).toFixed(2)), params.stock.delta * stock_price);
	await page.waitForSelector('td:nth-of-type(3)');
	let cur_amt = Number(await page.$eval('td:nth-of-type(3)', e => e.innerHTML));
	expectToEqual("stock amount change when buying stocks", cur_amt - prev_amt, params.stock.amount);
}
async function check_income(page)
{
	await page.waitForSelector('td:nth-of-type(2)');
	let prev_price = Number(await page.$eval('td:nth-of-type(2)', e => e.innerHTML));
	await page.waitForSelector('td:nth-of-type(4)');
	let prev_income = Number(await page.$eval('td:nth-of-type(4)', e => e.innerHTML));

	await delay(8000);

	await page.waitForSelector('td:nth-of-type(4)');
	let cur_income = Number(await page.$eval('td:nth-of-type(4)', e => e.innerHTML));
	await page.waitForSelector('td:nth-of-type(2)');
	let cur_price = Number(await page.$eval('td:nth-of-type(2)', e => e.innerHTML));
	await page.waitForSelector('td:nth-of-type(3)');
	let amt = Number(await page.$eval('td:nth-of-type(3)', e => e.innerHTML));
	expectToEqual("income change", (cur_income - prev_income).toFixed(2), ((cur_price - prev_price) * amt).toFixed(2));
}
async function sell_stock(page)
{
	await page.waitForSelector('b:nth-of-type(2)');
	let prev_balance = Number(await page.$eval('b:nth-of-type(2)', e => e.innerHTML));
	await page.waitForSelector('td:nth-of-type(3)');
	let prev_amt = Number(await page.$eval('td:nth-of-type(3)', e => e.innerHTML));
	await page.waitForSelector('td:nth-of-type(2)');
	let stock_price = Number(await page.$eval('td:nth-of-type(2)', e => e.innerHTML));
	await page.waitForSelector('.action_input');
	await page.focus('.action_input');
	await page.keyboard.type(params.stock.amount.toString());
	await page.click('.action_button:nth-of-type(2)');

	await delay(1000);

	await page.waitForSelector('b:nth-of-type(2)');
	let cur_balance = Number(await page.$eval('b:nth-of-type(2)', e => e.innerHTML));
	expectToLE("balance change when selling stocks", Math.abs(cur_balance.toFixed(2) - (prev_balance + stock_price * params.stock.amount).toFixed(2)), params.stock.delta * stock_price);
	await page.waitForSelector('td:nth-of-type(3)');
	let cur_amt = Number(await page.$eval('td:nth-of-type(3)', e => e.innerHTML));
	expectToEqual("stock amount change when selling stocks", prev_amt - cur_amt, params.stock.amount);
}

(async () => {
	const browser = await ppt.launch({headless: true});
	const page = await browser.newPage();
	await login(page);
	await open_stocks(page);
	await delay(2500);
	await buy_stock(page);
	await check_income(page);
	await sell_stock(page);

	//await page.screenshot({path: 'screen.png'});
	expectsEnd();
	process.exit(0);
})();
