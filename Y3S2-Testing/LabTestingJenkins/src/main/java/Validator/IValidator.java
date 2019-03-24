package Validator;
import Exceptions.ValidatorException;
public interface IValidator<E> {
    void validate(E entity) throws ValidatorException;
}