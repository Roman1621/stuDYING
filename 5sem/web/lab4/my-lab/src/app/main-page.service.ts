import { Injectable } from '@angular/core';
import {HttpClient} from "@angular/common/http";
import {HttpHeaders, HttpErrorResponse} from "@angular/common/http";

@Injectable({
  providedIn: 'root'
})
export class MainPageService {
  constructor(private http: HttpClient) { }
  getPhoto(id: number, getting: (photo: string) => void){
    this.http.post<Photo>('http://localhost:4300/user_photo', {id}).subscribe(res => {
      if(!res.error || res.error.length == 0) getting(res.photo);
    }, (err: HttpErrorResponse) => {});
  }
  uploadPhoto(id: number, photo_file: File, uploading: ()=> void){
    let form = new FormData();
    form.append('file', photo_file);
    let header = new HttpHeaders();
    header = header.set('id', JSON.stringify(id));
    this.http.post('http://localhost:4300/upload_photo', form, {headers: header}).subscribe(res=>{
      uploading();
    });
  }
  getInfo(id:number, gettingInfo: (name: string, mail: string, birth: string, status: string, role: string) => void){
    this.http.post<Info>("http://localhost:4300/user_info", {id}).subscribe(res =>{
      gettingInfo(res.name, res.mail, res.birth, res.status, res.role);
    });
  }
}

export interface Photo {
  error: string
  photo: string
}
export interface Info{
  name: string,
  mail: string,
  birth: string,
  role: string,
  status: string
}
