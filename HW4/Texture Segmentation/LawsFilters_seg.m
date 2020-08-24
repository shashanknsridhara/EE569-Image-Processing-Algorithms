function filterBank = LawsFilters_seg()
    filters = [[1 4 6 4 1];[-1 -2 0 2 1];[-1 0 2 0 -1];[-1 2 0 -2 1];[1 -4 6 -4 1]];
    filterBank = zeros(5,5);
    filterCount = 1;
    for i = 1:5
       for j=i:5
           filterBank(:,:,filterCount) =  filters(i,:)'*filters(j,:);
           filterCount = filterCount+1;
       end
    end
end