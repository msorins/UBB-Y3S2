import { Component, ViewChild, group } from '@angular/core';
import { DataService } from './data.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  @ViewChild('name') name;
  @ViewChild('group') group;
  @ViewChild('email') email;
  @ViewChild('tutor') tutor;
  students: any[];

  constructor(private dataService: DataService) {
    this.getStudent();
  }

  addStudent() {
    const name = this.name.nativeElement.value;
    const groupval = this.group.nativeElement.value;
    const emailval = this.email.nativeElement.value;
    const tutor = this.tutor.nativeElement.value;
    const student = {
      name: name,
      group: groupval,
      email: emailval,
      indrumator: tutor
    };

    const toNR = parseInt(groupval, 10);
    if ( !isNaN(toNR) ) {
      this.students.push(student);
    }

    this.dataService.addStudent(student);
  }

  getStudent() {
    this.dataService.getStudents().subscribe(data => {
      console.log(data);
      this.students = data;
    });
  }
}
