function exFive
    a = [2 4 6 8];
    f = [4 8 14 16];


    function ret = div_diff_table(a, f)
      [zzz, n] = size(a);
      
      table = a';
      table = [(0:(n-1))', table, f'];

      for i = 1:(n-1)
        a_diff = (table((i + 1):end, 2) - table(1:(end-i), 2));
        last_col = (table(2:(end-i+1), end) - table(1:end-i, end));
        new_col = last_col ./ a_diff;

        table = [table, [new_col; NaN(i, 1)]];
      end

      ret = table;
    end
    div_diff_table(a, f)
end