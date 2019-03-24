package Repository.MemoryRepository;
import Validator.IValidator;
import Domain.Student;

public class StudentRepo extends AbstractCrudRepo<String, Student> {
    public StudentRepo(IValidator<Student> v){ super(v);
    }
}