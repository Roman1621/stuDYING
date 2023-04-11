import {AfterViewInit, Component, ElementRef, OnInit, ViewChild} from '@angular/core';
import { Title } from '@angular/platform-browser';
import {HttpClient} from "@angular/common/http";

export interface Users{
  id: number
  photo: any
  name: string
  mail: string
  birth: any
  status: string
  role: string
  friends?: number
  news?: string
}
@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
  mail = ""
  is_admin = false;
  constructor(private titleService: Title) {
  }
  ngOnInit() {
    this.titleService.setTitle('Z-своих не бросаем');
  }
}
