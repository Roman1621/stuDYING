import { Component } from '@angular/core';
import {LoginService} from "../login.service";
import {Router} from "@angular/router";

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css'],
  providers: [ LoginService ]
})
export class LoginComponent {
  constructor(private login_service: LoginService) {
  }
  mail = ''
  password = ''
  login_button() {
    this.login_service.login(this.mail, this.password, ()=>{alert("Welcome to your profile"); window.location.href = "http://localhost:4200/main_page"}, ()=>{alert("Wrong login/password")})
  }
}
