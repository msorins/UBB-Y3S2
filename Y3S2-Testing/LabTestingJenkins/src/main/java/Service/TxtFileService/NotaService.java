package Service.TxtFileService;
import Domain.*;
import Repository.TxtFileRepository.NotaFileRepo;

public class NotaService extends AbstractService<Integer,Nota> {
    public NotaService(NotaFileRepo notaRepo){
        super(notaRepo);
    }
}
