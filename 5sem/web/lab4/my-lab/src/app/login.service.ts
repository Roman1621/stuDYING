import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Injectable({
  providedIn: "root"
})

export class LoginService {
  constructor(private http: HttpClient) {}
  login(mail: string, password: string, on_login: () => void, on_error: (msg: string) => void) {
    this.http.post<id_Response>("http://localhost:4300/login",
      {mail, password})
      .subscribe(res => {
        if(!res.error || res.error.length == 0){
          sessionStorage["my-lab_id"] = res.id;
          sessionStorage["my-lab_is_admin"] = res.is_admin;
          on_login();
        }
        else
          on_error(res.error);
      });
  }

  register(mail: string, name:string, birth: string, password: string, on_register: () => void, on_error: (msg: string) => void) {
    this.http.post<id_Response>("http://localhost:4300/register",
      {mail, password, name, birth})
      .subscribe(res => {
        if(res.error && res.error.length != 0)
          on_error(res.error);
        else
          on_register();
      });
  }
}

export interface id_Response {
  id: number
  error: string
  is_admin: boolean
}

