library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

use IEEE.NUMERIC_STD.ALL;


entity Linka_A is
    Port ( CLK : in  STD_LOGIC;
           LED : out  STD_LOGIC_VECTOR (7 downto 0);
           SEG : out  STD_LOGIC_VECTOR (6 downto 0);
           CE : in  STD_LOGIC;
           Q : out  STD_LOGIC_VECTOR (2 downto 0);
           RESET : in  STD_LOGIC);
end Linka_A;

architecture Behavioral of Linka_A is
    signal tmp: std_logic_vector(2 downto 0) := "000";
	 
	 
	 
begin
    process (CLK)
    begin
        if (CLK'event and CLK='1') then

			
			if (RESET='1') then
					tmp <= "000";
				
				elsif(CE = '1') then
					tmp <= std_logic_vector(unsigned(tmp) + 1);
				
				else
				
					tmp <= tmp;
				
				
				end if;
			end if;

    end process;

    Q <= tmp;
	 
	  with tmp SELect
		SEG<= "1111001" when "001",   --1
				"0100100" when "010",   --2
				"0110000" when "011",   --3
				"0011001" when "100",   --4
				"0010010" when "101",   --5
				"0000010" when "110",   --6
				"1111000" when "111",   --7
				"1000000" when others;   --0
				
	  with tmp SELect
		LED<= "10000000" when "001",   --2 takt
				"01000000" when "100",   --5
				"00010000" when "110",   --7
				"00000000" when others;   --1


end Behavioral;

