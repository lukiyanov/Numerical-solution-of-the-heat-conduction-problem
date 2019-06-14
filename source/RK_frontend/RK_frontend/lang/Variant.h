#pragma once

namespace lang
{
	// Отдельный enum для типа не нужен: куждый оператор и так знает, с каким типом он имеет дело.

	union Variant {
		double doubleValue;
		bool   boolValue;
	};

}