import { Injectable } from '@angular/core';
import {io} from 'socket.io-client';
import {HttpClient} from "@angular/common/http";
import {Socket} from "socket.io-client";
var socket: Socket

@Injectable({
  providedIn: 'root'
})
export class NewsService {
  constructor(private http: HttpClient) {socket = io("http://localhost:4300")}
  get_news(id:number, getting_news:(news:News[]) => void, on_error: (msg:string)=>void){
    this.http.post('http://localhost:4300/news', { id }).subscribe((res:any) => { if(!res.error || res.error.length == 0) getting_news(res.news); else(on_error(res.error))})
  }
  add_news(id:number, news_name: string, news_body: string, on_add:() => void, on_error: (msg:string)=>void){
    this.http.post('http://localhost:4300/add_news', { id, news_name, news_body}).subscribe((res:any) => { if(!res.error || res.error.length == 0) on_add(); else (on_error(res.error))})
  }
  onGetNews(socketfunc:()=> void){
    socket.removeAllListeners('news')
    socket.on('news', (message)=> socketfunc())
  }
}

export interface News{
  user_name: string,
  news_name: string,
  news_body: string
}
