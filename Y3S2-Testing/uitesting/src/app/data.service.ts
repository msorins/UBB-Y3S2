import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';


@Injectable()
export class DataService {

    constructor(private http: HttpClient) {

    }

    getStudents() {
        return this.http.get('http://localhost:8080/');
    }

    addStudent(student: any) {
        this.http.post('', student);
    }
}
