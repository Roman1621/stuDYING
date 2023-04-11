import {Component, Input, OnInit} from '@angular/core';
import { LoginService } from '../login.service';

@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.css'],
  providers: [ LoginService ]
})
export class RegisterComponent{
  constructor(private login_service: LoginService) {}
  mail = ''
  name = ''
  password = ''
  birth = ''

  register_button(){
    this.login_service.register(this.mail, this.password, this.name, this.birth, ()=>{alert("You register at SNFP")}, ()=>{alert("You already registered")})
  }
}
