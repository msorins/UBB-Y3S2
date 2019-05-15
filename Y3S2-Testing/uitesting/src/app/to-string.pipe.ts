import { Pipe, PipeTransform } from '@angular/core';

@Pipe({name: 'toString'})
export class ToStringPipe implements PipeTransform {
    transform(value: any) {
        return value.id + ' ' + value.name + ' ' + value.group + ' ' + value.indrumator + ' ' + value.email;
    }
}
