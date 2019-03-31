package Repository.MemoryRepository;

import Domain.Student;
import Domain.TemaLab;
import Exceptions.ValidatorException;
import Service.TxtFileService.TemaLabService;
import Validator.StudentValidator;
import Validator.TemaLabValidator;
import org.junit.Test;

import javax.xml.bind.ValidationException;

import static org.junit.Assert.assertTrue;

public class AssignmentRepositoryTest {


    @Test
    public void validTermenLimita() {
        TemaLabValidator vs=new TemaLabValidator();
        TemaLabRepo temaLabRepo = new TemaLabRepo(vs);
        TemaLab tema = new TemaLab(
                20,
                "testName",
                10,
                12

        );
        try {
            temaLabRepo.save(tema);
            assertTrue(true);
        }
        catch (Exception ex){
            assertTrue(!ex.getMessage().contains("Termen limita invalid"));
        }
    }

    @Test
    public void invalidTermenLimita(){
        TemaLabValidator vs=new TemaLabValidator();
        TemaLabRepo temaLabRepo = new TemaLabRepo(vs);
        TemaLab tema = new TemaLab(
                20,
                "testName",
                -1,
                10

        );
        try {
            temaLabRepo.save(tema);
            assertTrue(false);
        }
        catch (Exception ex){
            assertTrue(ex.getMessage().contains("Termen limita invalid"));
        }
    }

    @Test
    public void temaValida(){
        TemaLabValidator vs=new TemaLabValidator();
        TemaLabRepo temaLabRepo = new TemaLabRepo(vs);
        TemaLab tema = new TemaLab(
                20,
                "testName",
                -1,
                10

        );
        try {
            temaLabRepo.save(tema);
            assertTrue(true);
        }
        catch (Exception ex){
            assertTrue(!ex.getMessage().contains("Descriere tema invalida"));
        }
    }
    @Test
    public void temaInvalid(){
        TemaLabValidator vs=new TemaLabValidator();
        TemaLabRepo temaLabRepo = new TemaLabRepo(vs);
        TemaLab tema = new TemaLab(
                20,
                "",
                -1,
                10

        );
        try {
            temaLabRepo.save(tema);
            assertTrue(false);
        }
        catch (Exception ex){
            assertTrue(ex.getMessage().contains("Descriere tema invalida"));
        }
    }


}
