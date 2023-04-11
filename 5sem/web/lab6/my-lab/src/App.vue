<template style="margin: 0; padding: 0;">
	<div class="main">
    <div class="menu_pane">
      <router-link class="login_button" to="/login">Login</router-link>
      <router-link to="/trade">Stocks</router-link>
      <router-link to="/admin">Admin</router-link>
      <div class="login_name">{{$store.state.name}}</div>
    </div>
    <div class="content_pane">
      <router-view/>
    </div>
  </div>
</template>

<script>
import LoginService from './services/Login';

export default {
	name: 'App',
	components: {},

	created() {
		LoginService.login(this.axios, this.$store, ()=>{}, ()=>{});
	}
}
</script>

<style>
html, body {
  margin: 0px;
  padding: 0px;
  background: radial-gradient(white, black) no-repeat;
  min-height: 100vh;
  color: white;
}
#app{
  margin: 0 auto;
  padding: 0px;
}
.main{
  margin: 0;
  padding: 0;

}
.menu_pane {
  /*border: 2px white solid;*/
  width: 97vw;
  height: 10vh;
  border-radius: 5px;
}
a {
  /*border: 2px white solid;*/
  /*display: inline-grid;*/
	margin-right: 2vw;
  margin-top: 2vh;
	padding-left: 1vw;
	padding-right: 1vw;
	padding-top: 5vh;
	padding-bottom: 1vh;
  background-color: transparent;
  font-size: 2.5vh;
  color: white;
  border-radius: 5px;
}
.login_button{
  margin-top: 5vh;
}
.content_pane {
	margin-left: 1.5vw;
	margin-top: 1.5vh;
	width: 93vw;
	height: 85.5vh;
	padding-top: 1.5vh;
	padding-left: 1.5vw;
	padding-right: 1.5vw;
	background-color: transparent;
}

.login_name {
	float: right;
	margin-top: 1.5vh;
	color: white;
	font-size: 2.5vh;
	font-weight: bold;
  margin-right: 10px;
}
</style>
