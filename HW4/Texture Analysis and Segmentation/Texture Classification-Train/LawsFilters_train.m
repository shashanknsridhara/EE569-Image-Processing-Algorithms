% Name: Shashank Nelamangala Sridhara
% USC ID Number: 2082227554
% USC Email: nelamang@usc.edu
% Submission Date: 03/22/2020

function filterBank = LawsFilters_train()
    filters = [[1 4 6 4 1];[-1 -2 0 2 1];[-1 0 2 0 -1];[-1 2 0 -2 1];[1 -4 6 -4 1]];
    filterBank = zeros(5,5);
    filterCount = 1;
    for i = 1:5
       for j=1:5
           filterBank(:,:,filterCount) =  filters(i,:)'*filters(j,:);
           filterCount = filterCount+1;
       end
    end
end