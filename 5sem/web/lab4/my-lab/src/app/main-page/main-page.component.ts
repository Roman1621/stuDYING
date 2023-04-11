import {Component, OnInit} from '@angular/core';
import {MainPageService} from "../main-page.service";

@Component({
  selector: 'app-main-page',
  templateUrl: './main-page.component.html',
  styleUrls: ['./main-page.component.css']
})
export class MainPageComponent implements OnInit{
  constructor(private main_page_service: MainPageService) {setInterval(()=>{this.is_admin = sessionStorage["my-lab_is_admin"] === 'true'}, 500)}
  photo_user_url = ''
  puu_file: File | any = null;
  is_admin = false;
  name = ""
  mail = ""
  birth = ""
  status = ""
  role = ""

  ngOnInit() {
    this.main_page_service.getPhoto(parseInt(sessionStorage["my-lab_id"]), (photo: string) => {this.photo_user_url = photo;})
    this.main_page_service.getInfo(parseInt(sessionStorage["my-lab_id"]), (name: string, mail: string, birth: string, status: string, role: string) => {this.name = name; this.mail = mail; this.birth = birth; this.status = status; this.role = role})
  }

  select_photo_file(event: any){
    this.puu_file = event.target.files[0];
  }
  upload_photo(){
    this.main_page_service.uploadPhoto(parseInt(sessionStorage["my-lab_id"]), this.puu_file,
      () => this.main_page_service.getPhoto(parseInt(sessionStorage["my-lab_id"]),
        (photo: string) => {this.photo_user_url = photo;
        }))
  }
}
