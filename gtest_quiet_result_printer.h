// New BSD License
/*
Copyright 2012, Takazumi Shirayanagi

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation 
     and/or other materials provided with the distribution.
  3. the copyright holder's name is not used to endorse products 
     built using this software without specific written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef INCG_gtest_quiet_result_printer_H_
#define INCG_gtest_quiet_result_printer_H_

//! コンパクトなデフォルトコンソール出力イベントリスナー
class QuietResultPrinter : public ::testing::TestEventListener
{
public:
	QuietResultPrinter(::testing::TestEventListener* default_printer)
		: m_default_printer(default_printer)
	{}
	virtual ~QuietResultPrinter()
	{
		delete m_default_printer;
	}

	virtual void OnTestProgramStart(const ::testing::UnitTest& unit_test) { m_default_printer->OnTestProgramStart(unit_test); }

	virtual void OnTestIterationStart(const ::testing::UnitTest& unit_test,
		int iteration) { m_default_printer->OnTestIterationStart(unit_test, iteration); }

	virtual void OnEnvironmentsSetUpStart(const ::testing::UnitTest& unit_test) { m_default_printer->OnEnvironmentsSetUpStart(unit_test); }

	virtual void OnEnvironmentsSetUpEnd(const ::testing::UnitTest& unit_test) { m_default_printer->OnEnvironmentsSetUpEnd(unit_test); }

	virtual void OnTestCaseStart(const ::testing::TestCase& test_case) { m_default_printer->OnTestCaseStart(test_case); }

#if 0
	virtual void OnTestStart(const ::testing::TestInfo& test_info) {}

	virtual void OnTestPartResult(const ::testing::TestPartResult& test_part_result)
	{
		if( ::testing::UnitTest::GetInstance()->current_test_info() != NULL )
		{
			const ::testing::TestInfo& test_info = *::testing::UnitTest::GetInstance()->current_test_info();
			if( test_info.result()->Failed()
				&& test_info.result()->total_part_count() == 1 )
			{
				m_default_printer->OnTestStart(test_info);
			}
		}
		m_default_printer->OnTestPartResult(test_part_result);
	}
#else
	virtual void OnTestStart(const ::testing::TestInfo& test_info) { m_default_printer->OnTestStart(test_info); }

	virtual void OnTestPartResult(const ::testing::TestPartResult& test_part_result) { m_default_printer->OnTestPartResult(test_part_result); }
#endif

	virtual void OnTestEnd(const ::testing::TestInfo& test_info)
	{
		if( test_info.result()->Failed() )
		{
			// 失敗したときのみ出力する
			m_default_printer->OnTestEnd(test_info);
		}
	}

	virtual void OnTestCaseEnd(const ::testing::TestCase& test_case) { m_default_printer->OnTestCaseEnd(test_case); }

	virtual void OnEnvironmentsTearDownStart(const ::testing::UnitTest& unit_test) { m_default_printer->OnEnvironmentsTearDownStart(unit_test); }

	virtual void OnEnvironmentsTearDownEnd(const ::testing::UnitTest& unit_test) { m_default_printer->OnEnvironmentsTearDownEnd(unit_test); }

	virtual void OnTestIterationEnd(const ::testing::UnitTest& unit_test,
		int iteration) { m_default_printer->OnTestIterationEnd(unit_test, iteration); }

	virtual void OnTestProgramEnd(const ::testing::UnitTest& unit_test) { m_default_printer->OnTestProgramEnd(unit_test); }
private:
	::testing::TestEventListener* m_default_printer;
};

//! QuietResultPrinter に切り替え
inline void SetUpQuietResultPrinter(void)
{
	::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
	listeners.Append(new QuietResultPrinter(listeners.Release(listeners.default_result_printer())));
}

#endif
