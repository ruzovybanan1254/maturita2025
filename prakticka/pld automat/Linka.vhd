
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;


entity Linka is
    Port ( CLK : in  STD_LOGIC;
           RESET : in  STD_LOGIC;
           CE : in  STD_LOGIC;
           LED : out  STD_LOGIC_VECTOR (7 downto 0);
           SEG : out  STD_LOGIC_VECTOR (6 downto 0);
           q : out  STD_LOGIC_VECTOR (3 downto 0);
           AN : out  STD_LOGIC_VECTOR (3 downto 0));
end Linka;

architecture Behavioral of Linka is
signal tmp: std_logic_vector(3 downto 0) := "0000";

begin

    process (CLK)
    begin
		if (CLK'event and CLK='1') then			
				if(tmp = "1010") then
					tmp <= "0000";
				
				elsif (RESET='1') then
					tmp <= "0000";
				
				elsif(CE = '1') then
					tmp <= std_logic_vector(unsigned(tmp) + 1);
					
				else
					tmp <= tmp;
				end if;
				
				
		end if;
		end process;

		Q <= tmp;
		
		
		with tmp SELect
			SEG<= "1111001" when "0001",   --1
				"0100100" when "0010",   --2
				"0110000" when "0011",   --3
				"0011001" when "0100",   --4
				"0010010" when "0101",   --5
				"0000010" when "0110",   --6
				"1111000" when "0111",   --7
				"0000000" when "1000",   --8
				"0010000" when "1001",   --9
				"1000000" when others;   --0
				
		
				
		with tmp SELect
			LED<= 
				"11111111" when "0010",   --3
				"11111111" when "0100",   --5
				"11111111" when "0110",   --7
				"11111111" when "1000",   --9
				"00000000" when others;   --1





end Behavioral;

