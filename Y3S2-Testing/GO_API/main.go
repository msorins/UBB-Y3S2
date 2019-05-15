package main

import (
	"encoding/json"
	"fmt"
	"github.com/gorilla/mux"
	"log"
	"net/http"
)

type Student struct {
	Nume       string `json:"name"`
	Grupa      int    `json:"group"`
	Email      string `json:"email"`
	Indrumator string `json:"tutor"`
}

type API struct {
	students []Student
	router *mux.Router
}

func APIBuilder() API {
	// Create API Object
	newApi := API{}

	// Instantiate Routers
	newApi.router = mux.NewRouter()
	newApi.router.HandleFunc("/", newApi.GetStudents)
	http.Handle("/", newApi.router)

	// Add some mock data to students list
	newApi.students = append(newApi.students, Student{Nume: "Mircea Sorin", Grupa: 935, Email: "sorynsoo@gmail.com", Indrumator: "Tot Sorin"} )
	newApi.students = append(newApi.students, Student{Nume: "Nazarie Ciprian", Grupa: 935, Email: "nazacipri@hotmail.com", Indrumator: "Sorin"} )
	newApi.students = append(newApi.students, Student{Nume: "Peodor Taius", Grupa: 936, Email: "p@taius.com", Indrumator: "Sorin"} )

	return newApi
}

func (this *API) GetStudents (w http.ResponseWriter, r *http.Request) {
	this.enableCors(&w)
	response, _ := json.Marshal(this.students)
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(200)
	w.Write(response)
}

func (this *API) AddStudent(w http.ResponseWriter, r *http.Request) {
	//name := r.FormValue("nume")
}

func (this *API) enableCors(w *http.ResponseWriter) {
	(*w).Header().Set("Access-Control-Allow-Origin", "*")
}

func main() {
	api := APIBuilder()
	log.Fatal(http.ListenAndServe(":8080", api.router))
	fmt.Println(api.students)
}
