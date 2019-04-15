package Repository.MemoryRepository;


import Domain.Nota;
import Domain.Student;
import Domain.TemaLab;
import Validator.NotaValidator;
import Validator.StudentValidator;
import Validator.TemaLabValidator;
import org.junit.Test;

import static org.junit.Assert.assertTrue;

public class IntegrationTest {

    @Test
    public void testAddStudent(){
        StudentValidator studentValidator=new StudentValidator();
        StudentRepo repo = new StudentRepo(studentValidator);
        Student student = new Student(
                "testId",
                "testName",
                3112,
                "testMail",
                "testTeacher"
        );

        try{
            assertTrue(repo.findAll().spliterator().getExactSizeIfKnown()==0);
            repo.save(student);
            assertTrue(repo.findAll().spliterator().getExactSizeIfKnown()==1);
        }
        catch (Exception ex){
            assertTrue(false);
        }
    }

    @Test
    public void testAddAssignment() {
        TemaLabValidator labValidator=new TemaLabValidator();
        TemaLabRepo repoTema = new TemaLabRepo(labValidator);
        TemaLab tema = new TemaLab(
                20,
                "testName",
                10,
                12

        );

        try{
            assertTrue(repoTema.findAll().spliterator().getExactSizeIfKnown()==0);
            repoTema.save(tema);
            assertTrue(repoTema.findAll().spliterator().getExactSizeIfKnown()==1);
        }
        catch (Exception ex){
            assertTrue(false);
        }
    }

    @Test
    public void shouldAddGradeTest(){
        NotaValidator nv = new NotaValidator();
        NotaRepo notaRepo = new NotaRepo(nv);

        Nota nota = new Nota(1, "testId", 1, 10, null);
        try{
            notaRepo.save(nota);
            assertTrue(true);
        }catch(Exception ex){
            assertTrue(false);
        }
    }

    @Test
    public void inteGrationTesting(){
        this.shouldAddGradeTest();
        this.testAddAssignment();
        this.testAddStudent();
    }
}