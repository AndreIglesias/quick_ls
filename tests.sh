# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tests.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/11 06:11:43 by ciglesia          #+#    #+#              #
#    Updated: 2021/07/11 06:30:56 by ciglesia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

if [ -d tests ]; then
	rm -rf tests
fi

mkdir tests;
touch tests/file{1..5};
mkdir tests/dir{1..5};
touch tests/dir{1..5}/file{1..3};

chmod g+s tests/file1;
chmod u+s tests/file2;
chmod o+t tests/file3;
setfacl -m user:user:rwx tests/file4;
chmod 2775 tests/file5;
ln tests/file1 tests/file6;
ln -s tests/file6 tests/file7;

chmod g+s tests/dir1;
chmod u+s tests/dir2;
chmod o+t tests/dir3;
setfacl -m user:user:rwx tests/dir4;
chmod 2775 tests/dir5;
ln -s tests/dir1 tests/dir6;
ln -s tests/dir6 tests/dir7;
