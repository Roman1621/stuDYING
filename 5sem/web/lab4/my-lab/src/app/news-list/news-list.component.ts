import {Component, OnInit} from '@angular/core';
import {MainPageService} from "../main-page.service";
import {NewsService, News} from "../news.service";

@Component({
  selector: 'app-news-list',
  templateUrl: './news-list.component.html',
  styleUrls: ['./news-list.component.css']
})
export class NewsListComponent implements OnInit{
  photo_user_url = ""
  constructor(private news_service: NewsService, private main_page: MainPageService) {}
  news_list: News[] = [];
  news_name = ""
  news_body = ""
  ngOnInit() {
    this.news_service.onGetNews(()=> this.ngOnInit())
    this.news_service.get_news(sessionStorage["my-lab_id"], (news: News[]) => {this.news_list = news;}, (msg: string) => {alert(msg)})
    this.main_page.getPhoto(parseInt(sessionStorage["my-lab_id"]), (photo: string) => {this.photo_user_url = photo;})
  }
  add_news(){
    this.news_service.add_news(sessionStorage["my-lab_id"], this.news_name, this.news_body, () => {this.ngOnInit()}, (msg: string) => {alert(msg)})
  }
  return_to_main(){
    window.location.href = "http://localhost:4200/main_page";
  }
}
