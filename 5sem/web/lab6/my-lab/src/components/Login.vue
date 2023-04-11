<template>
	<div align=center style="margin-top: 30vh">
		<input type="text" placeholder="Input your token" class="login_textbox" v-model="token"/><br>
		<button class="login_button" v-on:click="login">Login</button>
		<div class="login_success" style="margin-top: 5vh">{{msg_success}}</div>
		<div class="login_error">{{msg_error}}</div>
	</div>
</template>

<script>
import LoginService from '../services/Login';

export default
{
	name: 'LoginComponent',
	components: {},

	data() { return { 
						token: "",
						msg_success: "",
						msg_error: ""
					}},
	methods: {
		login()
		{
			this.msg_success = "";
			this.msg_error = "";

			sessionStorage['token'] = this.token;
			LoginService.login(this.axios, this.$store,
			() => this.msg_success = "Successful login",
			(err) => this.msg_error = err);
		}
	}
}
</script>

<style scoped>
.login_button {
	background-color: transparent;
	color: black;
	font-size: 3vh;
}
.login_textbox {
	font-size: 3vh;
	margin-bottom: 1vh;
}

.login_success {
	color: #00cc00;
	font-size: 3vh;
	width: fit-content;
}
.login_error {
	color: #cc0000;
	font-size: 3vh;
	width: fit-content;
}
</style>
