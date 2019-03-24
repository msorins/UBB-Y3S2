package Repository.MemoryRepository;
import Validator.IValidator;
import Domain.Nota;

public class NotaRepo extends AbstractCrudRepo<Integer,Nota > {
    public NotaRepo(IValidator<Nota> v){ super(v);
    }
}